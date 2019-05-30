import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.Statement;
import java.sql.DriverManager;
import java.sql.SQLException;

public class SQLExample
{
	public static void main(String args[]) throws Exception
	{
		Class.forName("com.mysql.jdbc.Driver");

		String[] login = new String[6]; // host, port, db name, username, password, flags
		login[0] = "csdb.cs.eou.edu";
		login[1] = "3306";
		login[2] = "dbCButterworthTrack";
		login[3] = "cbutterworth";
		login[4] = "y3sh@llb3asgOds";
		login[5] = "?noAccessToProcedureBodies=true";
		
		int index = 1;
	}
	
	public static void addAthlete(String[] login, int index, String fName, String lName, String gender)
	{
		try
		{
			Connection conn = DriverManager.getConnection("jdbc:mysql://"
				+ login[0] + "/" + login[2] + login[5], login[3], login[4]);
			Statement stmt = conn.createStatement();
			
			boolean success = stmt.execute("INSERT INTO Athletes VALUES("
				+ index + ", " + fName + ", " + lName + ", " + gender + ", NULL");
				
			if (success)
			{
				System.out.println("Insert successful.");
			}
			else
			{
				System.out.println("Insert failed.");
			}
		}
		catch (SQLException ex)
		{
			System.out.println("SQLException: " + ex.getMessage());
			System.out.println("SQLState: " + ex.getSQLState());
			System.out.println("VendorError: " + ex.getErrorCode());
			ex.printStackTrace();
		}
	}
	
	public static void addResult(String[] login, int event, int athlete, int mark)
	{
		try
		{
			Connection conn = DriverManager.getConnection("jdbc:mysql://"
				+ login[0] + "/" + login[2] + login[5], login[3], login[4]);
			Statement stmt = conn.createStatement();
			
			boolean success = stmt.execute("INSERT INTO Results VALUES("
				+ athlete + ", " + event + ", " + mark + ", N");
				
			if (success)
			{
				System.out.println("Insert successful.");
			}
			else
			{
				System.out.println("Insert failed.");
			}
		}
		catch (SQLException ex)
		{
			System.out.println("SQLException: " + ex.getMessage());
			System.out.println("SQLState: " + ex.getSQLState());
			System.out.println("VendorError: " + ex.getErrorCode());
			ex.printStackTrace();
		}
	}
	
	public static void disqualify(String[] login, int event, int athlete)
	{
		try
		{
			Connection conn = DriverManager.getConnection("jdbc:mysql://"
				+ login[0] + "/" + login[2] + login[5], login[3], login[4]);
			Statement stmt = conn.createStatement();
			
			boolean success = stmt.execute("UPDATE Results SET DQ = 'Y' WHERE athleteID = "
				+ athlete + " AND eventID = " + event);
				
			if (success)
			{
				System.out.println("Update successful.");
			}
			else
			{
				System.out.println("Update failed.");
			}
		}
		catch (SQLException ex)
		{
			System.out.println("SQLException: " + ex.getMessage());
			System.out.println("SQLState: " + ex.getSQLState());
			System.out.println("VendorError: " + ex.getErrorCode());
			ex.printStackTrace();
		}
	}
	
	public static void disqualifyAll(String[] login, int athlete)
	{
		try
		{
			Connection conn = DriverManager.getConnection("jdbc:mysql://"
				+ login[0] + "/" + login[2] + login[5], login[3], login[4]);
			Statement stmt = conn.createStatement();
			
			boolean success = stmt.execute("UPDATE Results SET DQ = 'Y' WHERE athleteID = " + athlete);
				
			if (success)
			{
				System.out.println("Update successful.");
			}
			else
			{
				System.out.println("Update failed.");
			}
		}
		catch (SQLException ex)
		{
			System.out.println("SQLException: " + ex.getMessage());
			System.out.println("SQLState: " + ex.getSQLState());
			System.out.println("VendorError: " + ex.getErrorCode());
			ex.printStackTrace();
		}
	}
	
	public static void disqualifyAll(String[] login, int athlete)
	{
		try
		{
			Connection conn = DriverManager.getConnection("jdbc:mysql://"
				+ login[0] + "/" + login[2] + login[5], login[3], login[4]);
			Statement stmt = conn.createStatement();
			
			boolean success = stmt.execute("UPDATE Results SET DQ = 'Y' WHERE athleteID = " + athlete);
				
			if (success)
			{
				System.out.println("Update successful.");
			}
			else
			{
				System.out.println("Update failed.");
			}
		}
		catch (SQLException ex)
		{
			System.out.println("SQLException: " + ex.getMessage());
			System.out.println("SQLState: " + ex.getSQLState());
			System.out.println("VendorError: " + ex.getErrorCode());
			ex.printStackTrace();
		}
	}
	
	public static void displayResults(String[] login, int event)
	{
		try
		{
			Connection conn = DriverManager.getConnection("jdbc:mysql://"
				+ login[0] + "/" + login[2] + login[5], login[3], login[4]);
			Statement stmt = conn.createStatement();
			
			boolean gotResults = stmt.execute("SELECT * FROM Athletes UNION SELECT * FROM Results WHERE eventID = " + event);

			ResultSet rs = stmt.getResultSet();			
			rs.first();
			
			System.out.printf("%s | %-20s | %-40s | %-20s | %s | %s | %-10s | %s %n%n",
				"EventID", "Event Name", "Name", "School", "Place", "DQ", "Mark", "Score");
			
			while (gotResults)
			{
				String eName = rs.getString("eventName");
				String fName = rs.getString("firstName");
				String lName = rs.getString("lastName");
				String sName = rs.getString("school");
				int place = rs.getInt("place");
				String dq = rs.getString("dq");
				int mark = rs.getInt("result");
				int score = rs.getInt("score");
				System.out.printf("%-7d | %-20s | %-40s | %-20s | %s | %s | %-10s %d %n",
					event, eName, fName, lName, sName, place, dq, mark, score);
				gotResults = rs.next();
			}
		}
		catch (SQLException ex)
		{
			System.out.println("SQLException: " + ex.getMessage());
			System.out.println("SQLState: " + ex.getSQLState());
			System.out.println("VendorError: " + ex.getErrorCode());
			ex.printStackTrace();
		}
	}
	
	public static void scoreEvent(String[] login, int event)
	{
		try
		{
			Connection conn = DriverManager.getConnection("jdbc:mysql://"
				+ login[0] + "/" + login[2] + login[5], login[3], login[4]);
			Statement stmt = conn.createStatement();
			
			int[] scores = {10, 8, 6, 4, 2, 1};
			
			boolean gotResults = stmt.execute("SELECT place FROM Results WHERE eventID = " + event);

			ResultSet rs = stmt.getResultSet();			
			rs.first();
			
			while (gotResults)
			{
				int place = rs.getInt("Place");
				stmt.execute("UPDATE Results SET score = " + scores[place - 1] + " WHERE place = " + place);
				gotResults = rs.next();
			}
		}
		catch (SQLException ex)
		{
			System.out.println("SQLException: " + ex.getMessage());
			System.out.println("SQLState: " + ex.getSQLState());
			System.out.println("VendorError: " + ex.getErrorCode());
			ex.printStackTrace();
		}
	}
	
	public static void tooManyEvents(String[] login, int athlete)
	{
		try
		{
			Connection conn = DriverManager.getConnection("jdbc:mysql://"
				+ login[0] + "/" + login[2] + login[5], login[3], login[4]);
			Statement stmt = conn.createStatement();
			
			int eventCount = 0;
			
			boolean gotResults = stmt.execute("SELECT * FROM Results WHERE athleteID = " + athlete);

			ResultSet rs = stmt.getResultSet();			
			rs.first();
			
			while (gotResults)
			{
				eventCount++;
				gotResults = rs.next();
			}
			
			if (eventCount > 4)
			{
				stmt.execute("UPDATE Results SET dq = 'Y' WHERE athleteID = " + athlete);
			}
			else
			{
				System.out.println("Athlete is within bounds.");
			}
		}
		catch (SQLException ex)
		{
			System.out.println("SQLException: " + ex.getMessage());
			System.out.println("SQLState: " + ex.getSQLState());
			System.out.println("VendorError: " + ex.getErrorCode());
			ex.printStackTrace();
		}
	}
	
	public static void champion(String[] login)
	{
		try
		{
			Connection conn = DriverManager.getConnection("jdbc:mysql://"
				+ login[0] + "/" + login[2] + login[5], login[3], login[4]);
			Statement stmt = conn.createStatement();
			
			boolean gotResults = stmt.execute("SELECT * FROM Athletes WHERE")
		}
		catch (SQLException ex)
		{
			System.out.println("SQLException: " + ex.getMessage());
			System.out.println("SQLState: " + ex.getSQLState());
			System.out.println("VendorError: " + ex.getErrorCode());
			ex.printStackTrace();
		}
	}
}
